if ARGV.size != 1
  puts "usage: ruby genbench.rb <source filename>"
  exit
end

cflags ='-static -nostdlib'
otags = ['-O1', '-O2', '-O3']
scales = [10, 100, 1000, 10000, 100000, 1000000]
exe = ARGV.shift
basename = File.basename(exe, ".c")
gccpath = '../../bin/unicore32-linux-gcc-4.4.2'

`mkdir #{basename}`
otags.each do |otag|
  scales.each do |scale|
    cmd = "#{gccpath} #{cflags} #{otag} -D MAXN=#{scale} -D BENCH -o #{basename}/#{basename}#{otag}-#{scale} #{exe}"
    puts cmd
    `#{cmd}`
  end
end
