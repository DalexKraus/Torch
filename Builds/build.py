import os
import threading
import platform
from threading import Thread
from os.path import isfile, join

#Checksum file
cksumfile = 'Builds/out/chksums.res'

#Folders
rootdir         = './'
srcpath         = rootdir + 'src'
compileOutput   = 'Builds/out'
runpath       = rootdir + 'Builds/run'
resourcedirs    = ['shaders', 'textures']

#Compiler flags
libflags        = ' -lglfw3 -lopengl32 -lgdi32' if platform.system() == 'Windows' else ' -lglfw -framework opengl'
include         = ' -IBuilds/Dependencies/include'
libs            = ' -LBuilds/Dependencies/lib'
executable      = ' engine'
compilerCall    = 'g++ -g -Wall --std=c++17' + include + ' -c $SRC$ -o ' + compileOutput + '/$OUT$.o'
linkerCall      = 'g++ -g -Wall --std=c++17' + libs + ' ' +  '$OBJ$' + libflags + ' -o ' + executable


def isheader(filename):
    return filename.endswith('.h') or filename.endswith('.hpp')


def main():
    #Create compilation and executable output directories
    if not os.path.exists(compileOutput):
        os.mkdir(compileOutput)
    if not os.path.exists(runpath):
        os.mkdir(runpath)

    #Find all compilable files
    print('\n\nCollecting files ...\n')
    sources = collect_compilable_files()

    #Compile each file
    print('\nCompiling sources ...')
    compileThreads = []

    for file in sources:
        print('Compiling file \'' + file + '\'')
        #Compile source
        toAdd = Thread(target=compile_source, args=(file,))
        toAdd.start()
        compileThreads.append(toAdd)

    #Wait for threads to finish
    for thread in compileThreads:
        thread.join()

    #Link compiled object files
    objects = collect_objects()
    print('\nLinking ...')
    os.system(linkerCall.replace('$OBJ$', ' '.join(objects)))
    print('Moving executable ...')
    os.system('mv ' + executable + ' ' + runpath)

    #Copy resources
    print('Copying resources ...')
    copy_resources()

    print('[BUILD FINISHED]')

    #Launch the executable
    print('\n --- Launch ---')
    os.popen(runpath + '/' + executable.replace(" ", ""))


def compile_source(sourcefile):
    os.system(compilerCall.replace('$SRC$', srcpath + '/' + sourcefile).replace('$OUT$', os.path.splitext(sourcefile)[0]))


def collect_compilable_files():
    #Retrieve all compilable sources
    files = [f for f in os.listdir(srcpath) if isfile(join(srcpath, f)) 
        if (f.endswith('.cpp') or f.endswith('.c') or isheader(f))]

    #Sort files
    files.sort(key = lambda x: str(x.rsplit('.', 1)[1]), reverse=True)

    toCompile = []
    os.system('touch ' + cksumfile)
    cksumfilehandle = open(cksumfile, "r+")
    cksumfilecontent = cksumfilehandle.read()

    for file in files:
        #Parse checksum of source file
        cksumResult = os.popen('cksum ' + srcpath + '/' + file).read().split(' ')
        cksum = file + '=' + cksumResult[0] + '-' + cksumResult[1] + ';'
        
        #Determine if the source needs to be recompiled. (= The cksum has changed)
        needsCompile = True
        isInFile = False
        if file in cksumfilecontent:
            fileidx = cksumfilecontent.find(file)
            spaceridx = cksumfilecontent.find(';', fileidx)
            prevcksum = cksumfilecontent[fileidx:spaceridx + 1]
            isInFile = True

            if prevcksum == cksum:
                needsCompile = False
            #If a header file changed, the entire project needs to be recompiled.
            elif isheader(file):
                toCompile = files
                print('Header file \'' + file + '\' has changed, entire project needs to be recompiled.')
                break
        else:
            #Append to the list of files which need to be compiled (if it's not a header)
            if not isheader(file):
                toCompile.append(file)
            #Add checksum to the cksum file
            cksumfilehandle.write(str(cksum) + '\n')

        if needsCompile:
            print('{:30}'.format(file + ':') + 'Staged for compilation')
            #Update cksum in file
            if isInFile:
                cksumfilecontent = cksumfilehandle.read()
                cksumfilecontent.replace(prevcksum, cksum)
                cksumfilehandle.truncate()
                #cksumfilehandle.write(cksumfilecontent)
        else:
            print('{:30}'.format(file + ':') + 'No changes made')
        

    cksumfilehandle.close()
    return toCompile


def collect_objects():
    objects = [f for f in os.listdir(compileOutput) if isfile(join(compileOutput, f)) if (f.endswith('.o'))]
    for idx, obj, in enumerate(objects):
        objects[idx] = compileOutput + '/' + obj
    return objects


def copy_resources():
    for resourcefolder in resourcedirs:
        os.system('cp -r -f ' + rootdir + resourcefolder + ' ' + runpath + '/')
    return


if __name__ == '__main__':
    main()
