#!/usr/bin/env ruby

# SMTP client (Ruby version)
# Ouarrak Ayoub, 7/12/2014
# Version 1.0.0

# Usage: server.rb [options]

# Use option -h or --help to show help

require 'optparse'
require 'timeout'
require 'socket'

@options = {}
@port = 25
@server = 'localhost'

optparse = OptionParser.new do|opts|
   opts.banner = "Usage: smtp_client.rb [options]"
   options[:timeout] = 40

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