#!/usr/bin/python
#
# Author: Peter Hatina <phatina@redhat.com>
#
# This example is based upon openlmi-account provider. It issues
# EnumerateInstanceNames method, retrieves all the LMI_Account's instance names
# from the remote machine and prints them out.
#
# To make this example work, modify following variables:
#   hostname
#   username
#   password
#   cls

import lmiwbem

hostname = "hostname"
username = "username"
password = "password"
cls      = "class"

# Connect to CIMOM
conn = lmiwbem.WBEMConnection()
conn.connect(hostname, username, password)

# Enumerate instance names
inames = conn.EnumerateInstanceNames(
    cls, "root/cimv2")

# Do something with instance names
print inames

# Disconnect from CIMOM
conn.disconnect()
