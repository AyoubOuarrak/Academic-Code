
require 'optparse'
require 'timeout'
require 'socket'
require 'thread'

options = {}

optparse = OptionParser.new do|opts|
   opts.banner = "Usage: echotcp2-server.rb [options]"
   options[:port] = 25028
   options[:bufsize] = 100

   opts.on('-p', '--port PORT', 'port') do|port|
      options[:port] = port
   end

   opts.on('-b', '--bufsize', 'buffer size') do|buf|
      options[:bufsize] = buf
   end

   opts.on('-h', '--help', 'diplay help') do 
      puts opts
      exit
   end
end.parse!


def comunicationHandler
	
	
end

