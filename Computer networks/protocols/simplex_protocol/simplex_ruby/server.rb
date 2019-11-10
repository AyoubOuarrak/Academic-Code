#!/usr/bin/env ruby

# Simplex Sender (Ruby version)
# Ouarrak Ayoub, 7/12/2014
# Version 1.0.4

# Usage: server.rb [options]

# Use option -h or --help to show help

require 'optparse'
require 'timeout'
require 'socket'

options = {}

optparse = OptionParser.new do|opts|
   opts.banner = "Usage: server.rb [options]"
   options[:timeout] = 40
   options[:port] = 9999
   options[:bufsize] = 100

   opts.on('-t', '--timeout TIMEOUT', 'timeout') do|tim|
      options[:timeout] = tim
   end

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

puts "Started UDP server on #{options[:port]}..."
puts $!
begin
   #create new socket
   socket = UDPSocket.new

   #bind host and port
   socket.bind("0.0.0.0", options[:port])

   data, addr = socket.recvfrom(options[:bufsize])
   filename = data.split

   fout = File.open(filename[0], "w")

   pack = 1
   data, addr = socket.recvfrom(options[:bufsize])

   puts "Receiving data..."
   puts "from:  '%s'" % addr[2]

   #recive data from the sender
   while data != "nil" do 
      puts "receiving '%s'" % pack
      fout.write(data)

      begin
         timeout(options[:timeout]) do
            data, addr = socket.recvfrom(options[:bufsize])
         end
      rescue Timeout::Error
         puts "Timed out!"
         exit
      end

      pack = pack + 1
   end
rescue
   puts "An error occurred, please restart your computer, or format your pc"
ensure
   fout.close
   socket.close
end


