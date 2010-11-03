#!/usr/bin/env python

import argparse
import arff
from gac import *
import numpy
from util import *

def classify(instance, tree):
    if type(instance[-1]) is str:
        t = "DEFECT"
    else:
        t = "EFFORT"
    def walk(node):
        if (node.variance < node.weightedvariance()) or (node.left == None and node.right == None):
            if t == "DEFECT":
                return node.majorityclass()
            else:
                return numpy.median(transpose(node.data)[-1])                
        else:
            if node.right == None or node.left == None:
                if node.right == None:
                    return walk(node.left)
                else:
                    return walk(node.right)
            else:
                if node.right.weightedvariance() > node.left.weightedvariance():
                    return walk(node.left)
                else:
                    return walk(node.right)
    return walk(tree)

def main ():
    parser = argparse.ArgumentParser(description="Perform classifications using the TEAK method on a GAC tree")
    parser.add_argument('--arff', dest='arff', metavar='FILE', type=str, help='Specify arff file to use.')
    options = parser.parse_args()

    if options.arff == None:
        print "Your options don't please us."
        print "Reformatting /dev/sda1"
        exit(0)

    arfff = arff.Arff(options.arff)
    gactree = gac(arfff.data)
    gactree.varianceprune(1.1,1.1)
#    gactree.describe()
    print arfff.data[0][-1]
    print classify(arfff.data[0], gactree.nodes[0])

if __name__=='__main__':
    main()