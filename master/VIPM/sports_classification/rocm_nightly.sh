#!/bin/bash

echo now installing The Rock Nightly - SDK libs and devel...
uv pip install \
    --index https://rocm.nightlies.amd.com/v2/gfx120X-all/ \
	"rocm[libraries,devel]==7.13.0a20260315"
	# "rocm_sdk_core==7.13.0a20260315" \
	# "rocm_sdk_libraries_gfx120X_all==7.13.0a20260315" \
	# "rocm_sdk_devel==7.13.0a20260315"