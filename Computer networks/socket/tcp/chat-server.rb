#!/usr/bin/env ruby

# TCP server echo (Ruby version)
# Ouarrak Ayoub, 15/1/2014
# Version 1.0.0

# Usage: chat-server.rb [options]

# Use option -h or --help to show help

require 'optparse'
require 'socket'
require 'thread'

options = {}

optparse = OptionParser.new do|opts|
   opts.banner = "Usage: chat-server.rb [options]"
   options[:port] = 25028

   opts.on('-p', '--port PORT', 'port') do|port|
      options[:port] = port
   end

   opts.on('-h', '--help', 'diplay help') do 
      puts opts
      exit
   end
end.parse!


socket = TCPServer.new(options[:port])
messages = Queue.new
clients = []


Thread.start { # send chat messages to clients
    while msg = messages.pop;
        clients.each { |s|
            (s << msg).flush rescue IOError
        }
    end
}

print "Server started on port : #{options[:port]}"

loop {
    Thread.start(socket.accept) { |sock|
        clients << sock
        begin
            while line = sock.gets;  
                @mss = "#{line.chomp!}"
                if @mss == "quit"
                    puts ' '
                    abort('Quitting...')
                else
                    messages << ": #{@mss} \r\n"
                end
            end
            
        rescue
            bt = $!.backtrace * "\n  "
            ($stderr << "error: #{$!.inspect}\n  #{bt}\n").flush
        
        ensure
            clients.delete sock
            sock.close
        end
    }
}
