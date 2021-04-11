#!/bin/sh
time /home/zjw/document/study/perf_tracer/f_profile
cat /sys/kernel/debug/tracing/trace_stat/function0 | head -n 15
cat /sys/kernel/debug/tracing/trace_stat/function2 | head -n 15
