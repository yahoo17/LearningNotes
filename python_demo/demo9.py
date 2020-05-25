import logging
logging.basicConfig(level=logging.INFO)
def foo(s):
    n=int(s)
    assert n!=0,'n is zero error!'
    return 10/n

def main():
    foo('0')

# main()

def foo2(s):
    n=int(s)
    logging.info('n=%s!'%n)
    return 10/n

foo2('1')