# The evaluation image: Eclipse 4diac FORTE 3.3.0 with the filling module's block types, built from
# source, and the Python tools (planner, checker, synchroniser, evaluation).

# --- FORTE --------------------------------------------------------------------------------------
FROM debian:trixie-slim AS forte
RUN apt-get update && apt-get install -y --no-install-recommends \
        build-essential cmake git ca-certificates python3 libmodbus-dev \
    && rm -rf /var/lib/apt/lists/*

# open62541, the OPC UA stack FORTE 3.3 builds against; single-threaded, since a PUBLISH during an
# OPC UA method call deadlocks the multi-threaded stack.
RUN git clone --depth 1 --branch v1.5.4 --recurse-submodules --shallow-submodules \
        https://github.com/open62541/open62541.git /src/open62541 \
    && cmake -S /src/open62541 -B /build/open62541 -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=OFF \
        -DUA_NAMESPACE_ZERO=FULL -DUA_MULTITHREADING=0 -DUA_ENABLE_ENCRYPTION=OFF \
    && cmake --build /build/open62541 -j"$(nproc)" && cmake --install /build/open62541

# FORTE 3.3.0 with the patches in forte/patches (README there).
RUN git clone --depth 1 --branch 3.3.0 https://github.com/eclipse-4diac/4diac-forte.git /src/forte
COPY forte/patches /src/patches
RUN cd /src/forte && for p in /src/patches/*.patch; do git apply "$p"; done
COPY forte/CMakeLists.txt /src/build/CMakeLists.txt
COPY forte/types /src/build/types
RUN cmake -S /src/build -B /build/forte -DCMAKE_BUILD_TYPE=Release -DFORTE_SOURCE=/src/forte \
        -DFORTE_ARCHITECTURE=Posix -DFORTE_IO=ON -DFORTE_MODULE_IOSTUBS=ON \
        -DFORTE_COM_ETH=ON -DFORTE_COM_FBDK=ON -DFORTE_COM_LOCAL=ON -DFORTE_COM_RAW=ON \
        -DFORTE_COM_MODBUS=ON -DFORTE_COM_OPC_UA=ON \
        -DFORTE_MODULE_CONVERT=ON -DFORTE_MODULE_IEC61131=ON -DFORTE_MODULE_UTILS=ON \
        -DFORTE_MODULE_RECONFIGURATION=ON -DFORTE_MODULE_RT_Events=ON -DFORTE_MODULE_SIGNALPROCESSING=ON \
        -DFORTE_EventChainEventListSize=1024 -DFORTE_EventChainExternalEventListSize=1024 \
        -DFORTE_CommunicationInterruptQueueSize=64 \
    && cmake --build /build/forte -j"$(nproc)" --target forte \
    && cmake --install /build/forte --prefix /opt/forte

# --- Tools --------------------------------------------------------------------------------------
FROM python:3.11-slim-trixie
RUN apt-get update && apt-get install -y --no-install-recommends libmodbus5 git \
    && rm -rf /var/lib/apt/lists/*
COPY --from=forte /opt/forte/bin/forte /usr/local/bin/forte
WORKDIR /repo
COPY pyproject.toml README.md ./
COPY src ./src
RUN pip install --no-cache-dir -e ".[eval]"
COPY . .
ENV PYTHONUTF8=1 FORTE=/usr/local/bin/forte
