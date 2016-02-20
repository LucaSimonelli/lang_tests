# run it as
# fab -f fabfile.py azure1  what_is_my_name

from fabric.api import *
import fabric
import sys
import os.path
import os
import ConfigParser
import boto.ec2
import boto.exception
import time
import urllib2
from urllib2 import URLError

# imports for self-signed cert
from OpenSSL import crypto, SSL
from socket import gethostname
from pprint import pprint
from time import gmtime, mktime
from os.path import exists, join

def mytest():
    env.hosts = ['kitt']
    env.user = 'luca'
    env.key_filename = '~/.ssh/local_key'
    #env.password = 'blablabla123@|'
    print "LUCA env.sudo_prompt=\"%s\"" % env.sudo_prompt
    print "env=%s" % (env,)

def what_is_my_name():
    run('whoami')

def update_apt_get():
    """ For completeness, apt-get update
    """
    sudo('apt-get update')
    #run('apt-get update')
