#!/usr/bin/python
# coding=gbk
 
import argparse

# 假设这个是一个network 的自动测试工具，名叫ntf
# 接收三个参数，测试case名称，网络拓扑名称，还有运行在哪个os上。
# 如果将这三个参数都设置为optional参数，那么当执行这个命令时，在命令行里输入：
# ntf_optional --case "icmp6" --topology "two_node" --os linux

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--case",  help="the case you want to execute")
    parser.add_argument("--topology",  help="network topology")
    parser.add_argument("--os",  help="os deploy your software")
    nc = parser.parse_args()
    
    print(nc)

