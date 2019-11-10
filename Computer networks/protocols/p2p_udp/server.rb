#!/usr/bin/env ruby

# p2p server (Ruby version)
# Ouarrak Ayoub, 7/12/2014
# Version 1.0.4

# Usage: server.rb [options]
# Use option -h or --help to show help

require 'optparse'
require 'socket'
BasicSocket.do_not_reverse_lookup = true

options = {}

optparse = OptionParser.new do|opts|
   opts.banner = "Usage: server.rb [options]"
   options[:port] = 25028

   opts.on('-p', '--port PORT', 'port') do|port|
      options[:port] = port
   end

   opts.on('-h', '--help', 'diplay help') do 
      puts opts
      exit
   end
end.parse!

begin
   # Create socket and bind to address
   @host = "0.0.0.0"
   @socket = UDPSocket.new
   @socket.setsockopt(Socket::SOL_SOCKET, Socket::SO_BROADCAST, 1)
   @socket.bind(@host, options[:port])
   @clientPorts = []

   puts "UDP Server started..."
   while true
      msg =  @socket.recvfrom(2024)[0]
      nickname = @socket.recvfrom(2024)
      
      Thread.new(nickname) do | clientAddress |
        puts "Nickname: " + nickname[0]
        puts "Host: " + nickname[1][2]
        #puts "Port: " + nickname[1][1]
        puts "Has sent : " + msg 
        puts $!

         unless @clientPorts.include? clientAddress[1]
            @clientPorts << clientAddress[1]
         end
         broadcast(msg, @clientPorts)
      end
   end

   def broadcast(data, clients)                   
      puts clients
      clients.each do | client |
         @socket.send(data, @host, client)
      end
   end
rescue SocketError
   puts "Error happens when i tried to connect to the server"
   puts $!

ensure
   @socket.close
end

