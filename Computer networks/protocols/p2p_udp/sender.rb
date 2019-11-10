#!/usr/bin/env ruby

# p2p udp sender (Ruby version)
# Ayoub Ouarrak, 16/12/2014
# Version 1.0.0

# Usage: sender.rb [options]
# Use option -h or --help to show help

require 'optparse'
require 'socket'

options = {}
optparse = OptionParser.new do | opts |
   opts.banner = "Usage sender.rb [options]"
   options[:server] = "127.0.0.1"
   options[:nick] = "user"
   options[:port] = 25028
   options[:message] = ""

   opts.on('-s', '--server SERVER', 'Server IP') do | server |
      options[:server] = s
   end

   opts.on('-n', '--nickname NICKNAME', 'User nickname') do | nick |
      options[:nick] = nick
   end

   opts.on('-p', '--port PORT', 'Port') do | port |
      options[:port] = port
   end

   opts.on('-m', '--message MESSAGE', 'Message to send') do | msg |
      options[:message] = msg
   end

   opts.on('-h', '--help', 'display help') do
      p opts
      exit
   end
end.parse!

begin
   socket = UDPSocket.new
   socket.connect(options[:server],options[:port])
   #socket.setsockopt(Socket::SOL_SOCKET,Socket::SO_BROADCAST, 1)
   while true 
      msg = gets.chomp
      socket.send (msg),0
      socket.send (options[:nick]),0
      puts "Message sent"
   end
rescue SocketError
   puts "Error happens when i tried to connect to the server"
   puts $!

ensure
   socket.close
end

