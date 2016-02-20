import logging

logging.basicConfig()
logger = logging.getLogger()

try:
    raise Exception("LUCA Message")

except Exception, exc:
    logger.exception(exc)
    print "Exception handled"
