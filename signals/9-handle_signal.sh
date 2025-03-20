#!/bin/bash
for s in ABRT IO TERM; do trap 'echo Nope' SIG$s; done