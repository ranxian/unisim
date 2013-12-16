require 'terminal-table'

testexes = ['quicksort', 'mergesort', 'heapsort', 'bubblesort', 'selectsort', 'insertsort']
testscale = [10, 100, 1000, 10000, 100000]#, 100000, 1000000]
otags = ['-O1', '-O2', '-O3']
Resultdir = './results'

def result_name(exe, scale, otag)
  "#{exe}#{otag}-#{scale}.res"
end

def result_path(exe, scale, otag)
  File.join(Resultdir, exe, result_name(exe, scale, otag))
end

def calc(file, n)
  line1 = file.gets
  line2 = file.gets
  inst_cnt1, ncycle1, nstall1, nbubble1, nforward1, misspred1 = line1.split(" ").map(&:to_i)
  inst_cnt2, ncycle2, nstall2, nbubble2, nforward2, misspred2 = line2.split(" ").map(&:to_i)
  
  ncycle = ncycle2 - ncycle1
  nstall = nstall2 - nstall1
  nbubble = nbubble2 - nbubble1
  nforward = nforward2 - nforward1
  misspred = misspred2 - misspred1
  
  ninst = inst_cnt2 - inst_cnt1
  cpi = Float(ncycle) / ninst
  cpe = Float(ncycle) / n
  ipe = Float(ninst) / n
  bpi = Float(nbubble) / ninst
  spi = Float(nstall) / ninst
  mpi = Float(misspred) / ninst
  fpi = Float(nforward) / ninst

  return [ninst, cpi, cpe, ipe, bpi, spi, mpi, fpi].map { |f| f.round(2) }
end

result = File.open("./results/result.txt", "w")

results = []
testexes.each do |exe|
  testscale.each do |scale|
    otags.each do |otag|
      path = result_path(exe, scale, otag)
      next if not File.exist?(path)
      File.open(path) do |f|
        # inst, cpi, cpe, ipe = calc(f, scale)
        results << [result_name(exe, scale, otag), *calc(f, scale)]
      end
    end
  end
  results << :separator
end

table = Terminal::Table.new do |t|
  t.headings = ['program', 'nInst', 'CPI', 'CPE', 'IPE', 'BPI', 'SPI', 'MPI', 'FPI']
  t.rows = results
end

puts table
result.close