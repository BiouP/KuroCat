#!/usr/bin/env python3
"""Send a Codex lifecycle event to the local KuroCat window."""

import json
import os
from pathlib import Path
import re
import shlex
import socket
import sys


EVENTS = {
    "UserPromptSubmit": "start",
    "Stop": "stop",
    "Interrupt": "interrupt",
    "SessionEnd": "close",
}


def send_event(payload):
    if not isinstance(payload, dict):
        return
    event_name = payload.get("hook_event_name")
    if not isinstance(event_name, str) or event_name not in EVENTS:
        return
    event = EVENTS[event_name]
    session = payload.get("session_id")
    turn = payload.get("turn_id") or "session"
    identifier = r"[A-Za-z0-9_.-]{1,100}"
    if not isinstance(session, str) or not re.fullmatch(identifier, session):
        return
    if not isinstance(turn, str) or not re.fullmatch(identifier, turn):
        return
    key = session if event == "close" else f"{session}:{turn}"
    runtime = os.environ.get("XDG_RUNTIME_DIR") or os.environ.get("XDG_CACHE_HOME") or Path.home() / ".cache"
    path = Path(runtime) / "kurocat-codex.sock"
    with socket.socket(socket.AF_UNIX, socket.SOCK_DGRAM) as client:
        client.setblocking(False)
        client.sendto(f"{event} {key}".encode("ascii"), str(path))


def main():
    if sys.argv[1:] == ["--config"]:
        command = " ".join(shlex.quote(part) for part in (sys.executable, str(Path(__file__).resolve())))
        handler = {"type": "command", "command": command, "timeout": 1}
        print(json.dumps({"hooks": {event: [{"hooks": [handler]}] for event in EVENTS}}, indent=2))
        return

    try:
        send_event(json.load(sys.stdin))
    except (OSError, ValueError):
        # A missing window, a full socket or invalid input should never block Codex.
        pass
    print("{}")


if __name__ == "__main__":
    main()
