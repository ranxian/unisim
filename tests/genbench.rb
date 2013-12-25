cflags ='-static -nostdlib'
exes = ['heapsort', 'mergesort', 'insertsort', 'selectsort', 'quicksort', 'bubblesort']
otags = ['-O1', '-O2', '-O3']
scales = [10, 100, 1000, 10000, 100000, 1000000]
arg = ARGV.shift
gccpath = '../../bin/unicore32-linux-gcc-4.4.2'


exes.each do |exe|
  next if arg && arg != exe
  `mkdir #{exe}` if !File.directory?(exe)
  otags.each do |otag|
    scales.each do |scale|
      cmd = "#{gccpath} #{cflags} #{otag} -D MAXN=#{scale} -D BENCH -o #{exe}/#{exe}#{otag}-#{scale} #{exe}.c"
      puts cmd
      `#{cmd}`
    end
  end
end