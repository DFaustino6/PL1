from os import X_OK
import random
import logging
import threading
import time

def is_odd(n):
	return n%2 > 0

def p(n):
	if not is_odd(n):
		print("Since n is not odd, this program will generate n+1 perfect magic square")
		n+=1
	magicSquare = [[0 for x in range(n)]
				for y in range(n)]

	# initialize position of 1
	i = n / 2
	j = n - 1

	# Fill the magic square
	# by placing values
	num = 1
	while num <= (n * n):
		if i == -1 and j == n:  # 3rd condition
			j = n - 2
			i = 0
		else:

			# next number goes out of
			# right side of square
			if j == n:
				j = 0

			# next number goes
			# out of upper side
			if i < 0:
				i = n - 1

		if magicSquare[int(i)][int(j)]:  # 2nd condition
			j = j - 2
			i = i + 1
			continue
		else:
			magicSquare[int(i)][int(j)] = num
			num = num + 1

		j = j + 1
		i = i - 1  # 1st condition

	# Printing magic square
	File_object = open(r"inputs/p"+str(n)+".txt","w+")
	for i in range(0, n):
		#print("PLine: "+ str(i))
		for j in range(0, n):            
			if j != 0:
				File_object.write(" ")
			File_object.write(str(magicSquare[i][j]))
		File_object.write(' ')

def i(size):
	start_num = 1
	File_object = open(r"inputs/i"+str(size)+".txt","w+")
	for start_num in range(size):
		next_num = start_num+1
		#print("ILine: "+ str(start_num))
		for y in range(size):
			if next_num > size:
				next_num = 1
			if y != 0:
				File_object.write(" ")
			File_object.write(str(next_num))
			next_num+=1
		File_object.write(' ')

def r(size):
	File_object = open(r"inputs/r"+str(size)+".txt","w+")
	for start_num in range(size):
		#print("RLine: "+ str(start_num))
		for y in range(size):
			next_num = random.randint(1,size)
			if y != 0:
				File_object.write(" ")
			File_object.write(str(next_num))
			next_num+=1
		File_object.write(' ')

def main():
	size = int(input("Choose size, beware 10k+ will take a while: "))
	if size <= 2:
		print("Value must be > 2")
		exit()
	iThread = threading.Thread(target=i,args=(size,))
	rThread = threading.Thread(target=r,args=(size,))
	iThread.start()
	rThread.start()
	
	iThread.join()
	rThread.join()
	p(size)

	if not is_odd(size):
		size_p = size+1
	else: size_p = size
	print("Created three files i"+str(size)+".txt and r"+str(size)+".txt and a file p" + str(size_p)+".txt")

if __name__ == "__main__":
	main()

