import os
from os.path import isfile, join

#Checksum file
cksumfile = 'out/chksums.res'

#Folders
rootdir     = '../'
srcpath     = rootdir + 'src'
compileOutput = 'out'

#Compiler flags
libflags        = ' -lglfw3 -lopengl32 -lgdi32'
include         = ' -IDependencies/include'
libs            = ' -LDependencies/lib'
executable      = ' engine'
compilerCall    = 'g++ -g -Wall --std=c++17' + include + libs + ' -c $SRC$' + libflags + ' -o ' + compileOutput + '/$OUT$.o'
linkerCall      = 'g++ -g -Wall --std=c++17' + libs + ' ' +  '$OBJ$' + libflags + ' -o' + executable

def main():
    #Find all compilable files
    sources = collect_compilable_files()

    #Create compilation output directory
    if not os.path.exists(compileOutput):
        os.mkdir(compileOutput)

    #Compile each file
    print('--- Compilation Stage ---')
    for idx, file in enumerate(sources):
        print('Compiling file \'' + file + '\'')
        #Compile source
        #os.system(compilerCall.replace('$SRC$', srcpath + '/' + file).replace('$OUT$', os.path.splitext(file)[0]))
        print('Done. [' + str(idx) + ']')

    #Link compiled object files
    objects     = collect_objects()

    print('---   Linking Stage   ---')
    #os.system(linkerCall.replace('$OBJ$', ' '.join(objects)))


def collect_compilable_files():
    #Retrieve all compilable sources
    files = [f for f in os.listdir(srcpath) if isfile(join(srcpath, f)) if (f.endswith('.cpp') or f.endswith('.c'))]
    toCompile = []
    cksumfilehandle = open(cksumfile, "r+")
    for file in files:
        #Parse checksum for source file
        cksumResult = os.popen('cksum ' + srcpath + '/' + file).read().split(' ')
        cksum = file + '=' + cksumResult[0] + '-' + cksumResult[1] + ';'
        
        #Determine if the source needs to be recompiled. (= The cksum has changed)
        
        if file in cksumfilehandle.readlines():
            print("is present")
            print(get_cksum_for_file(cksumfilehandle, file))
        else:
            print("not present")
            #Append to the list of files which need to be compiled
            toCompile.append(file)
            #Add checksum to the cksum file
            cksumfilehandle.write(str(cksum) + '\n')
        
    cksumfilehandle.close()

    return toCompile

def get_cksum_for_file(cksumfilehandle, filename):
    content = cksumfilehandle.readlines()
    fileidx = content.find(filename)
    spaceridx = content.find(';', fileidx)
    return content[fileidx:spaceridx]

def collect_objects():
    objects = [f for f in os.listdir(compileOutput) if isfile(join(compileOutput, f))]
    for idx, obj, in enumerate(objects):
        objects[idx] = compileOutput + '/' + obj
    
    return objects


if __name__ == '__main__':
    main()
