#!/usr/bin/env python

import sys

def htmlfixup(s):
    return s.replace('<','&lt;').replace('>','&gt;')

### ENTRY ###
out = sys.stdout
inp = sys.stdin

for line in inp:
    line = line.rstrip('\n\r')
    if line[0] == '-':
        out.write('<div style="font-family: monospace; font-size: 12px; white-space: pre; color: #cc0000;">')
    elif line[0] == '+':
        out.write('<div style="font-family: monospace; font-size: 12px; white-space: pre; color: #008800;">')
    elif line[0] == '@':
        out.write('<div style="font-family: monospace; font-size: 12px; white-space: pre; color: #990099;">')
    elif line[0] == '=':
        out.write('<div style="font-family: monospace; font-size: 12px; white-space: pre; color: #000088;">')
    else:
        out.write('<div style="font-family: monospace; font-size: 12px; white-space: pre; color: #000000;">')
    out.write(htmlfixup(line))
    out.write('</div>\n')
