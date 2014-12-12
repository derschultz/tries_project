#!/usr/bin/python

import argparse
import random
import struct
import sys

parser = argparse.ArgumentParser(description='Generate some random integers with no duplicates, and write them in binary to disk.')
parser.add_argument('-s', '--size', help='integer length in bytes', choices=[4,8], type=int, default=4)
parser.add_argument('-c', '--count', help='number of integers to generate', type=int, default=1000)
parser.add_argument('-o', '--outfile', help='name of file to write output to (default:<count>.<size>.out)', default=None, type=str)
parser.add_argument('-v', '--verbose', help='be verbose', action='store_true')

args = parser.parse_args()
if args.outfile is None:
    args.outfile = "%d.%d.out" % (args.count, args.size)

if args.verbose:
    print "Generating %d unique integers of size %d bytes and writing them out to %s." % (
            args.count, args.size, args.outfile)

struct_format = 'I' if args.size is 4 else 'Q'

s = set()
while len(s) < args.count:
    s.add(random.getrandbits(args.size * 8))

if args.verbose:
    print "Done with generation, writing out file."

with open(args.outfile, 'wb') as f:
    for x in s:
        f.write(struct.pack(struct_format, x))

if args.verbose:
    print "Done writing out file."
