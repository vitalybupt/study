#!/usr/bin/python
# coding=gbk
 
import argparse

# ���������һ��network ���Զ����Թ��ߣ�����ntf
# ������������������case���ƣ������������ƣ������������ĸ�os�ϡ�
# ���������������������Ϊoptional��������ô��ִ���������ʱ���������������룺
# ntf_optional --case "icmp6" --topology "two_node" --os linux

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--case",  help="the case you want to execute")
    parser.add_argument("--topology",  help="network topology")
    parser.add_argument("--os",  help="os deploy your software")
    nc = parser.parse_args()
    
    print(nc)

