#!/usr/bin/env ruby

# Simplex Sender (Ruby version)
# Giuseppe Petrosino, 5/12/2014
# Version 1.0.3

# Usage: sender.rb [options]

# Use option -h or --help to show help

require 'optparse'
require 'socket'

# hash contenente tutte le opzioni
options = {}

optparse = OptionParser.new do|opts|
	opts.banner = "Usage: sender.rb [options]"

	options[:server] = '127.0.0.1'
	options[:port] = 9999
	options[:filein] = "/etc/issue"
	options[:fileout] = "temp"
	options[:bufsize] = 100
	options[:verbose] = false

	opts.on( '-s', '--server SERVER', 'Server name' ) do|serv|
	    options[:server] = serv
	end
	opts.on( '-p', '--port PORT', 'Port') do|port|
		options[:port] = port
	end
	opts.on( '-i', '--inputfile FILE', 'Input file name') do|fin|
		options[:filein] = fin
	end
	opts.on( '-o', '--outputfile FILE', 'Output file name') do|fout|
		options[:fileout] = fout
	end
	opts.on( '-b', '--bufsize SIZE', 'Buffer size' ) do|sz|
		options[:bufsize] = sz
	end
	opts.on( '-v', '--verbose', 'Show activity info') do
		options[:verbose] = true
	end

	opts.on( '-h', '--help', 'Display this screen' ) do
		p opts
		exit
	end
end

# parsing delle opzioni secondo le regole definite sopra
optparse.parse!

if options[:verbose]
	puts "Sending file #{options[:filein]}"
	puts "to server: #{options[:server]}"
	puts "at port: #{options[:port]}"
end

f = File.open(options[:filein], "r")

begin
	sock = UDPSocket.new()
	sock.connect(options[:server],options[:port])

	# invio del nome del file + la dimensione in bytes del buffer
	sock.send (options[:fileout] + " " + options[:bufsize].to_s),0

	while true do
		# lettura del buffer
		buffer = f.read(options[:bufsize])

		if buffer == nil
			sock.send "nil", 0
			break
		end

		puts "==================BUFFER==================" if options[:verbose]
		puts buffer if options[:verbose]
		puts "==========================================" if options[:verbose]

		# invio del buffer
		bytes_sent = sock.send buffer, 0
	end

	puts "#{bytes_sent} bytes sent."

rescue SystemCallError
	puts "Read from file #{options[:filein]} failed:"
	puts $!

rescue SocketError
	puts "An error occurred connecting with server #{options[:server]} at port #{options[:port]}:"
	puts $!

ensure
	f.close
	sock.close
end
