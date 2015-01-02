#!/usr/bin/python -tt

#the purpose of this script is to, given a csv of results in the expected format produced by the trie program, sort the results into multiple files, named for the input file, trie type, integer length used, and operation done, with each line corresponding to the count of integers and the time taken for each operation

#s -> success, f -> failed
#i -> insert, s -> search, d -> delete
#t -> total, s -> each
m = {   4: 's_i_t',
        5: 's_i_e',
        6: 'f_i_t',
        7: 'f_i_e',
        8: 's_s_t',
        9: 's_s_e',
        10: 's_d_t',
        11: 's_d_e',
        12: 'f_d_t',
        13: 'f_d_e',
        14: 'f_s_t',
        15: 'f_s_e'}

import sys

input_file = sys.argv[1]
prefix = '.'.join(input_file.split('.')[0:2])
data = {}

with open(input_file, 'r') as infile:
    for ln in infile:
        split = ln.split(',')
        count = split[0]
        int_len = split[1]
        trie_type = split[2]
        for op in range(3,15):
            dkey = "%s.%s.%s" % (trie_type, int_len, m[op+1])
            if dkey not in data:
                data[dkey] = []
            data[dkey].append("(%s,%s)" % (count, split[op]))

for k in data:
    with open('%s.%s.csv' % (prefix, k), 'w') as ofile:
        for x in data[k]:
            ofile.write("%s\n" % x)
