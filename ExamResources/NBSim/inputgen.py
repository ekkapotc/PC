import random
import sys

numParticles = int(sys.argv[1])
fileName = str(sys.argv[2])

with open(fileName,'w') as writer:
    
    writer.write('{0}\n'.format(numParticles))
    
    for i in range(0,numParticles):
        
        mass = random.uniform(0.1,20.0)
        
        px = random.uniform(-500,+500)
        py = random.uniform(-500,+500)
        
        vx = random.uniform(-100.0,+100.0)
        vy = random.uniform(-100.0,+100.0)
        
        writer.write('{0} {1} {2} {3} {4}\n'.format(mass,px,py,vx,vy))
    
