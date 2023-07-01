TUNE=base
EXT=gcc43-64bit
NUMBER=429
NAME=mcf
SOURCES= mcf.c mcfutil.c readmin.c implicit.c pstart.c output.c treeup.c \
	 pbla.c pflowup.c psimplex.c pbeampp.c
EXEBASE=mcf
NEED_MATH=yes
BENCHLANG=C
ONESTEP=
CONESTEP=

BENCH_CFLAGS     = -DWANT_STDC_PROTO
CC               = clang-12
COPTIMIZE        = -O3 
CXX              = /usr/bin/g++
CXXOPTIMIZE      = -O3  
FC               = /usr/bin/gfortran
FOPTIMIZE        = -O3  
FPBASE           = yes
OS               = unix
PORTABILITY      = -DSPEC_CPU_LP64
absolutely_no_locking = 0
abstol           = 
action           = validate
allow_extension_override = 0
backup_config    = 1
baseexe          = mcf
basepeak         = 1
benchdir         = benchspec
benchmark        = 429.mcf
binary           = 
bindir           = exe
build_in_build_dir = 1
builddir         = build
bundleaction     = 
bundlename       = 
calctol          = 0
changedmd5       = 0
check_integrity  = 0
check_md5        = 0
check_version    = 0
clean_between_builds = no
command_add_redirect = 0
commanderrfile   = speccmds.err
commandexe       = mcf_base.gcc43-64bit
commandfile      = speccmds.cmd
commandoutfile   = speccmds.out
commandstdoutfile = speccmds.stdout
compareerrfile   = compare.err
comparefile      = compare.cmd
compareoutfile   = compare.out
comparestdoutfile = compare.stdout
compile_error    = 0
compwhite        = 
configdir        = config
configpath       = /home/juan.salamanca/spec-cpu2006/config/myconf.cfg
copies           = 1
datadir          = data
default_size     = ref
delay            = 0
deletebinaries   = 0
deletework       = 0
dependent_workloads = 0
difflines        = 10
dirprot          = 511
endian           = 12345678
env_vars         = 0
exitvals         = spec_exit
expand_notes     = 0
expid            = 
ext              = gcc43-64bit
fake             = 0
feedback         = 1
flag_url_base    = http://www.spec.org/auto/cpu2006/flags/
floatcompare     = 
help             = 0
http_proxy       = 
http_timeout     = 30
hw_avail         = Dec-9999
hw_cpu_char      = 
hw_cpu_mhz       = 9999
hw_cpu_name      = Intel Core i7-4770
hw_disk          = 8.1 TB  add more disk info here
hw_fpu           = Integrated
hw_memory001     = 15.561 GB fixme: If using DDR3, format is:
hw_memory002     = 'N GB (M x N GB nRxn PCn-nnnnnR-n, ECC)'
hw_model         = System Model Name
hw_nchips        = 1
hw_ncores        = number of cores enabled
hw_ncoresperchip = number of cores manufactured into each chip
hw_ncpuorder     = 1,2 chips
hw_nthreadspercore = number of threads enabled per core
hw_ocache        = None
hw_other         = None
hw_pcache        = 9999 KB I + 9999 KB D on chip per core
hw_scache        = 9999 KB I+D on chip per core
hw_tcache        = 9999 MB I+D on chip per chip
hw_vendor        = System Vendor
ignore_errors    = yes
ignore_sigint    = 0
ignorecase       = 
info_wrap_columns = 50
inputdir         = input
iteration        = -1
iterations       = 1
keeptmp          = 0
license_num      = 0
line_width       = 0
locking          = 1
log              = CPU2006
log_line_width   = 0
log_timestamp    = 0
logname          = /home/juan.salamanca/spec-cpu2006/result/CPU2006.312.log
lognum           = 312
mach             = default
mail_reports     = all
mailcompress     = 0
mailmethod       = smtp
mailport         = 25
mailserver       = 127.0.0.1
mailto           = 
make             = specmake
make_no_clobber  = 0
makeflags        = 
max_active_compares = 0
mean_anyway      = 0
min_report_runs  = 3
minimize_builddirs = 0
minimize_rundirs = 0
name             = mcf
need_math        = yes
no_input_handler = close
no_monitor       = 
note_preenv      = 0
notes_os_000     = 'ulimit -s unlimited' was used to set environment stack size
notes_plat_sysinfo_000 =  Sysinfo program /home/juan.salamanca/spec-cpu2006/Docs/sysinfo
notes_plat_sysinfo_005 =  $Rev: 6775 $ $Date:: 2011-08-16 \#$ 8787f7622badcf24e01c368b1db4377c
notes_plat_sysinfo_010 =  running on pinguim Sun Apr 19 13:52:05 2015
notes_plat_sysinfo_015 = 
notes_plat_sysinfo_020 =  This section contains SUT (System Under Test) info as seen by
notes_plat_sysinfo_025 =  some common utilities.  To remove or add to this section, see:
notes_plat_sysinfo_030 =    http://www.spec.org/cpu2006/Docs/config.html\#sysinfo
notes_plat_sysinfo_035 = 
notes_plat_sysinfo_040 =  From /proc/cpuinfo
notes_plat_sysinfo_045 =     model name : Intel(R) Core(TM) i7-4770 CPU @ 3.40GHz
notes_plat_sysinfo_050 =        1 "physical id"s (chips)
notes_plat_sysinfo_055 =        8 "processors"
notes_plat_sysinfo_060 =     cores, siblings (Caution: counting these is hw and system dependent.  The
notes_plat_sysinfo_065 =     following excerpts from /proc/cpuinfo might not be reliable.  Use with
notes_plat_sysinfo_070 =     caution.)
notes_plat_sysinfo_075 =        cpu cores : 4
notes_plat_sysinfo_080 =        siblings  : 8
notes_plat_sysinfo_085 =        physical 0: cores 0 1 2 3
notes_plat_sysinfo_090 =     cache size : 8192 KB
notes_plat_sysinfo_095 = 
notes_plat_sysinfo_100 =  From /proc/meminfo
notes_plat_sysinfo_105 =     MemTotal:       16317348 kB
notes_plat_sysinfo_110 =     HugePages_Total:       0
notes_plat_sysinfo_115 =     Hugepagesize:       2048 kB
notes_plat_sysinfo_120 = 
notes_plat_sysinfo_125 =  /usr/bin/lsb_release -d
notes_plat_sysinfo_130 =     Ubuntu 12.04.3 LTS
notes_plat_sysinfo_135 = 
notes_plat_sysinfo_140 =  From /etc/*release* /etc/*version*
notes_plat_sysinfo_145 =     debian_version: wheezy/sid
notes_plat_sysinfo_150 =     os-release:
notes_plat_sysinfo_155 =        NAME="Ubuntu"
notes_plat_sysinfo_160 =        VERSION="12.04.3 LTS, Precise Pangolin"
notes_plat_sysinfo_165 =        ID=ubuntu
notes_plat_sysinfo_170 =        ID_LIKE=debian
notes_plat_sysinfo_175 =        PRETTY_NAME="Ubuntu precise (12.04.3 LTS)"
notes_plat_sysinfo_180 =        VERSION_ID="12.04"
notes_plat_sysinfo_185 = 
notes_plat_sysinfo_190 =  uname -a:
notes_plat_sysinfo_195 =     Linux pinguim 3.8.0-29-generic \#42~precise1-Ubuntu SMP Wed Aug 14 16:19:23
notes_plat_sysinfo_200 =     UTC 2013 x86_64 x86_64 x86_64 GNU/Linux
notes_plat_sysinfo_205 = 
notes_plat_sysinfo_210 =  run-level 2 2015-04-13 14:43
notes_plat_sysinfo_215 = 
notes_plat_sysinfo_220 =  SPEC is set to: /home/juan.salamanca/spec-cpu2006
notes_plat_sysinfo_225 =     Filesystem              Type  Size  Used Avail Use% Mounted on
notes_plat_sysinfo_230 =     maritaca:/volume1/homes nfs   8.1T  5.4T  2.8T  67% /home
notes_plat_sysinfo_235 = 
notes_plat_sysinfo_240 =  (End of data from sysinfo program)
notes_submit_000 = 'numactl' was used to bind copies to the cores.
notes_submit_005 = See the configuration file for details.
notes_wrap_columns = 0
notes_wrap_indent =   
num              = 429
obiwan           = 
os_exe_ext       = 
output           = asc
output_format    = asc,csv,html
output_root      = 
outputdir        = output
parallel_setup   = 1
parallel_setup_prefork = 
parallel_setup_type = fork
parallel_test    = 0
parallel_test_submit = 0
parallel_test_workloads = 
path             = /home/juan.salamanca/spec-cpu2006/benchspec/CPU2006/429.mcf
plain_train      = 1
power            = 0
preenv           = 1
prefix           = 
prepared_by      = juan.salamanca  (is never output, only tags rawfile)
ranks            = 1
rate             = 0
realuser         = your name here
rebuild          = 0
reftime          = reftime
reltol           = 
reportable       = 0
resultdir        = result
review           = 0
run              = all
rundir           = run
runspec          = /home/juan.salamanca/spec-cpu2006/bin/runspec --config=myconf.cfg --size=test --noreportable --tune=base --iteration=1 mcf
safe_eval        = 1
section_specifier_fatal = 1
sendmail         = /usr/sbin/sendmail
setpgrp_enabled  = 1
setprocgroup     = 1
setup_error      = 0
shrate           = 0
sigint           = 2
size             = test
size_class       = test
skipabstol       = 
skipobiwan       = 
skipreltol       = 
skiptol          = 
smarttune        = base
specdiff         = specdiff
specmake         = Makefile.YYYtArGeTYYYspec
specrun          = specinvoke
speed            = 0
srcalt           = 
srcdir           = src
srcsource        = /home/juan.salamanca/spec-cpu2006/benchspec/CPU2006/429.mcf/src
stagger          = 10
strict_rundir_verify = 0
submit_default   = $BIND $command
sw_avail         = May-2010
sw_base_ptrsize  = 64-bit
sw_compiler      = gcc, g++ & gfortran 4.3.4
sw_file          = nfs
sw_os001         = Ubuntu 12.04.3 LTS
sw_os002         = 3.8.0-29-generic
sw_other         = None
sw_peak_ptrsize  = 64-bit
sw_state         = Run level 2 (add definition here)
sysinfo_program  = specperl /home/juan.salamanca/spec-cpu2006/Docs/sysinfo
table            = 1
teeout           = yes
teerunout        = yes
test_date        = Apr-2015
test_sponsor     = Test Sponsor (Optional, defaults to hw_vendor)
tester           = (Optional, defaults to hw_vendor)
top              = /home/juan.salamanca/spec-cpu2006
train_with       = train
tune             = base
uid              = 1169
unbuffer         = 1
update-flags     = 0
use_submit_for_speed = 0
username         = juan.salamanca
vendor           = anon
vendor_makefiles = 0
verbose          = 5
version          = 0
version_url      = http://www.spec.org/auto/cpu2006/current_version
worklist         = list
OUTPUT_RMFILES   = inp.out mcf.out
