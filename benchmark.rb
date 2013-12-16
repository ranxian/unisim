exe = './unisim'
testdir = './tests'
testexes = ['quicksort', 'mergesort', 'bubblesort', 'selectsort', 'heapsort', 'insertsort']
testscale = [10, 100, 1000, 10000, 100000]#, 100000, 1000000]
otags = ['-O1', '-O2', '-O3']

target = ARGV.shift

testexes.each do |testexe|
  next if target && testexe != target
  unless File.directory?("results/#{testexe}")
    `mkdir results/#{testexe}`
  end
	testscale.each do |scale|
    if ['bubblesort', 'selectsort', 'insertsort'].include?(testexe) && scale >= 10000
      next
    end
		otags.each do |otag|
			path = File.join(testdir, testexe, "#{testexe}#{otag}-#{scale}")
      cmd = "#{exe} #{path} > ./results/#{testexe}/#{testexe}#{otag}-#{scale}.res"
			puts cmd
			`#{cmd}`
		end
	end
end
