import time

def procedure():
   time.sleep(3.12)

tx= time.time()

procedure()

ty  = time.time() - tx

print ty
