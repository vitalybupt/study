#!/usr/bin/env python3

import setuptools
import os

REQS=[]   # internal dependencies

setuptools.setup(
    name="py_cci",
    version=os.environ.get('PKG_PYTHON_VERSION', '0.1'),
    description="crack code interview in python",
    url="https://github.com/vitalybupt/study.git",
    author="junwei.zhang",
    author_email="vitaly1979@hotmail.com",
    license="MIT",
    install_requires=REQS,
    python_requires='>=3',
)
