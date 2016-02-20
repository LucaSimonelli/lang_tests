import logging


def foo():
    print ("foo called")
    return "I'm foo"

logger = logging.getLogger()

logger.setLevel(logging.WARNING)

logger.debug("1) %s" % foo())
logger.debug("2) %s", foo())
