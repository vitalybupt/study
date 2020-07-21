#!/usr/bin/python

import argparse


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("target", nargs='?', metavar="test cases", help="the case you like to run")
    parser.add_argument("--verbosity", choices=["none", "info", "debug"], dest='loglevel',default="info", help="increase output verbosity")
    
    parser.parse_args()

    
