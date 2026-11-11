"""modreg serve: the skill service (``modreg.service``) for the web UI, on the AASs of an AAS server.

    modreg serve --basyx http://localhost:8081            # on http://0.0.0.0:8090
"""
import argparse
import sys

from .service import AasServer, SkillService, serve


def main(argv=None) -> int:
    parser = argparse.ArgumentParser(prog="modreg", description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = parser.add_subparsers(dest="command", required=True)
    p = sub.add_parser("serve", help="run the skill service")
    p.add_argument("--bind", default="0.0.0.0")
    p.add_argument("--listen", type=int, default=8090, metavar="PORT")
    p.add_argument("--basyx", help="AAS server to read from and publish to, e.g. http://<host>:8081")
    args = parser.parse_args(argv)

    server = serve(SkillService(AasServer(args.basyx) if args.basyx else None), args.bind, args.listen)
    print(f"skill service on {args.bind}:{args.listen}; AAS server {args.basyx or 'none'}", flush=True)
    try:
        server.serve_forever()
    except KeyboardInterrupt:
        pass
    return 0


if __name__ == "__main__":
    sys.exit(main())
