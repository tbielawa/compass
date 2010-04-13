#!/usr/bin/env python

import sys
import re

infile = open(sys.argv[1], 'r')
mcost = []
roimpact = []
mreffect = []
rapl = []
oweight = []

for line in infile:
    line = line.replace("ddpData->","")
    line = line.replace("["," ")
    line = line.replace("]"," ")
    line = line.replace(";","")
    line = line.replace("\n","")
    if re.match("^ *mCost", line):
        mcost.append(line.split("=")[1])
    if re.match("^ *roImpact", line):
        line = line.replace("="," ")
        split = line.split(" ")
        s = "(make-ro-impact"
        s = s + " :r " + split[3]
        s = s + " :o " + split[5]
        s = s + " :impact " + split[7]
        s = s + ")"
        roimpact.append(s)
    if re.match("^ *mrEffect", line):
        line = line.replace("="," = ")
        split = line.split(" ")
        s = "(make-mr-effect "
        s = s + " :m " + split[3]
        s = s + " :r " + split[5]
        s = s + " :effect " + split[8]
        s = s + ")"
        mreffect.append(s)
    if re.match("^ *rAPL", line):
        rapl.append(line.split("=")[1])
    if re.match("^ *oWeight", line):
        oweight.append(line.split("=")[1])


print "(make-ddp-model"        

s = ":o-weight (list"
for weight in oweight:
    s = s + " " + weight
s = s + ")"
print s

s = ":m-cost (list"
for cost in mcost:
    s = s + " " + cost
s = s + ")"
print s

s = ":r-apl (list"
for risk in rapl:
    s = s + " " + risk
s = s + ")"
print s

print ":ro-impacts (list"
for var in roimpact:
    print var
print ")"

print ":mr-effects (list"
for var in mreffect:
    print var
print ")"

print ")"
