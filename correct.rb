TESTSUITE = ['test1', 'test2', 'test3', 'test4', 'test5', 'test6', 'test7', 'test8', 'test9', 'test10', 
              'bubblesort', 'heapsort', 'mergesort', 'selectsort', 'insertsort', 'quicksort'
              ]

TESTDIR = './tests'
UNIGCC = '../bin/unicore32-linux-gcc-4.4.2'

def clean
  TESTSUITE.each do |testcase|
    File.delete(testcase) if File.exists?(testcase)
    File.delete(testcase + '.res') if File.exists?(testcase + '.res')
    File.delete(testcase + '-X86') if File.exists?(testcase + '-X86')
    File.delete(testcase + '-X86.res') if File.exists?(testcase + '-X86.res')
  end
  puts 'cleaned.'
end

ntest = 0
passed = 0
target = ARGV.shift

begin
  TESTSUITE.each do |testcase|
    next if target && target != testcase
    printf "%-24s", "testing #{testcase}..."
    unc_compile_cmd = "#{UNIGCC} -static -nostdlib -O1 -o #{testcase} #{TESTDIR}/#{testcase}.c && ./unisim ./#{testcase} > #{testcase}.res"
    if target
      unc_compile_cmd << '&& cat ' + testcase + '.res'
    end
    x86_compile_cmd = "gcc -o #{testcase}-X86 -DX86 #{TESTDIR}/#{testcase}.c && ./#{testcase}-X86 > #{testcase}-X86.res"
    res = `#{unc_compile_cmd}`
    if target
      puts res
    end
    `#{x86_compile_cmd}`

    f1 = File.open("#{testcase}-X86.res", "r")
    f2 = File.open("#{testcase}.res", "r")

    ok = true
    loop do
      line = f1.gets
      break unless line
      line2 = f2.gets
      if line != line2
        ok = false and break
      end
    end

    printf "%30s", ok ? "\e[32m[ PASS ]\e[0m\n" : "\e[31m[ #{"FAIL"} ]\e[0m\n"
    ntest += 1
    passed += 1 if ok
  end

  printf "%d/%d tests passed.\n", passed, ntest
ensure
  unless target
    clean
  end
end
