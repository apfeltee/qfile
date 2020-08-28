#!/usr/bin/ruby

begin
  ARGV.each do |arg|
    File.open(arg, "rb") do |fh|
      printf("%s: %p\n", arg, fh.read(10).bytes)
    end
  end
end


