require 'terminal-table'

testexes = ['quicksort', 'mergesort', 'heapsort', 'bubblesort', 'selectsort', 'insertsort']
# testexes = ['quicksort', 'mergesort']
testscale = [10, 100, 1000, 10000, 100000]#, 100000, 1000000]
# testscale = [100000]#, 100000, 1000000]
otags = ['-O1', '-O2', '-O3']
# otags = ['-O1']
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
  inst_cnt2, ncycle2, nstall2, nbubble2, nforward2, misspred2, dmiss, dhit, imiss, ihit = line2.split(" ").map(&:to_i)
  
  ncycle = ncycle2 - ncycle1
  nstall = nstall2 - nstall1
  nbubble = nbubble2 - nbubble1
  nforward = nforward2 - nforward1
  misspred = misspred2 - misspred1

  dmem_access = dmiss + dhit
  imem_access = imiss + ihit
  icache_hit_rate = Float(ihit) * 100 / (ihit + imiss)
  dcache_hit_rate = Float(dhit) * 100 / (dhit + dmiss)

  ncycle += imem_access * (1 - icache_hit_rate/100) * (100 - 1)
  ncycle += dmem_access * (1 - dcache_hit_rate/100) * (100 - 1)
  
  ninst = inst_cnt2 - inst_cnt1
  cpi = Float(ncycle) / ninst
  cpe = Float(ncycle) / n
  ipe = Float(ninst) / n
  bpi = Float(nbubble) / ninst
  spi = Float(nstall) / ninst
  mpi = Float(misspred) / ninst
  fpi = Float(nforward) / ninst

  return [ninst, cpi, cpe, ipe, bpi, spi, mpi, fpi, imem_access, dmem_access, icache_hit_rate, dcache_hit_rate].map { |f| f.round(2) }
end

jsdatum = File.open("jsdatum.dat", "w")
collect = []
headings = ['program', 'nInst', 'CPI', 'CPE', 'IPE', 'BPI', 'SPI', 'MPI', 'FPI', 'IMEM', 'DMEM', 'IHR', 'DHR']
code = "dataset = ["
results = []
testexes.each do |exe|
  testscale.each do |scale|
    otags.each do |otag|
      path = result_path(exe, scale, otag)
      next if not File.exist?(path)
      File.open(path, 'r') do |f|
        # inst, cpi, cpe, ipe = calc(f, scale)
        data = calc(f, scale)
        results << [result_name(exe, scale, otag), *data]
        name = "#{exe[0]}#{otag[1..-1]}#{scale}"
        code << "{"
        code << "name: \"#{name}\","
        code << headings[1..-1].each_with_index.map { |heading, index| "#{heading}: #{data[index]}" }.join(", ")
        code << "},\n"
		collect << data[7];

      end
    end
  end
  results << :separator
end
puts collect

code << "];\n"
jsdatum.puts code

jsdatum.close

table = Terminal::Table.new do |t|
  t.headings = headings
  t.rows = results
end

puts table
