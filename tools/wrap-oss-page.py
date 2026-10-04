#!/usr/bin/env python3
"""Wrap one retrieved open-source document as a corpus page.

The article (from the first h1) is the retrieved text.  The notice before
that heading is this project's, so a reader can see the capture and the
licence conditions without those words being mistaken for the original.
``page_parse.article_html`` starts at the first h1, which is what the
knowledge base quotes.
"""

import html
import os
import sys


def wrap(title, body, front):
    return (
        "<!DOCTYPE html>\n<html>\n<head>\n<meta charset=\"utf-8\">\n"
        "<title>Text rendering of " + html.escape(title) + "</title>\n"
        "</head>\n<body>\n"
        + front
        + "<h1>" + html.escape(title) + "</h1>\n<pre>\n"
        + html.escape(body).rstrip() + "\n</pre>\n</body>\n</html>\n"
    )


def main():
    title, body_path, front_path, out_path = sys.argv[1:5]
    body = open(body_path, encoding="utf-8").read()
    front = open(front_path, encoding="utf-8").read()
    os.makedirs(os.path.dirname(out_path), exist_ok=True)
    with open(out_path, "w", encoding="utf-8") as fh:
        fh.write(wrap(title, body, front))


if __name__ == "__main__":
    main()
