#!/usr/bin/python

from arff import *
import csv
import numpy
import matplotlib.lines as lines
import matplotlib.pyplot as plt
from optparse import OptionParser
from util import *

class CompassGraph:
	East = None
	West = None
	data = []
	DataCoordinates = []
	Classes = []

	def __init__(self, InputData):
		self.data = InputData
		(self.East, self.West) = self.FindPoles(InputData)
		(self.DataCoordinates, self.Classes) = self.ComputeCoordinates()

	def WriteToPNG(self,filename,n):
		self.DataCoordinates = self.DataCoordinates.transpose()
		fig = plt.figure()
		ax1 = fig.add_axes([0.1,0.1,0.85,0.85])
		ticks = []
		for i in range(n):
			ticks.append( ( float(i)+1.0 )* (1.0/float(n) ) )
		ax1.set_xticks(ticks)
		ax1.set_yticks(ticks)
		plt.title(filename)
		plt.xlabel("x")
		plt.ylabel("y")
		for ax in fig.axes:
			ax.grid(True)

		if isinstance(self.Classes[0][0],str):
			for i in range(len(self.DataCoordinates[0])):
				if self.Classes[i][0].upper() == "TRUE":
					ax1.plot(self.DataCoordinates[0][i],self.DataCoordinates[1][i],"bo")
				else:
					ax1.plot(self.DataCoordinates[0][i],self.DataCoordinates[1][i],"ro")
		else:
			# we're going to color by highest and lowest.  Best of luck to me.
			# begin by normalizing the effort scores so we get a fluent gradient
			MaxScore=0
			MinScore=999999999
			NormalData=[]
			# find our min and max scores.
			for i in range(len(self.data)):
				if self.data[i][len(self.data[i])-1] < MinScore:
					MinScore = self.data[i][len(self.data[i])-1]
				if self.data[i][len(self.data[i])-1] > MaxScore:
					MaxScore = self.data[i][len(self.data[i])-1]
			# set the normalized values
			for i in range(len(self.data)):
				NormalData.append((self.data[i][len(self.data[i])-1]-MinScore)/(MaxScore-MinScore))
			# now, draw the data
			for i in range(len(self.DataCoordinates[0])):
				ax1.plot(self.DataCoordinates[0][i],self.DataCoordinates[1][i],'o',color=[1-NormalData[i],NormalData[i],0])
			

		ax1.set_xbound(0,1)
		ax1.set_ybound(0,1)
		plt.show()

				

	def ComputeCoordinates(self):
		d = distance(self.East,self.West)
		MaxX = 0
		MaxY = 0
		DataCoordinates = None
		# Compute (x,y) coordinates for each instance
		for instance in self.data:
			a = distance(self.East,instance)
			b = distance(self.West,instance)
			x = (b**2 - d**2 - a**2) / (-2 * d)
			if x > MaxX:
				MaxX = x
			y = math.sqrt(a**2 - x**2)
			if y > MaxY:
				MaxY = y
			if DataCoordinates is None:
				DataCoordinates = numpy.array([x,y])
				Classes = numpy.array([instance[len(instance)-1]])
			else:
				DataCoordinates = numpy.vstack((DataCoordinates,numpy.array([x,y])))
				Classes = numpy.vstack((Classes,numpy.array([instance[len(instance)-1]])))
		# Normalize coordinates
		for datum in DataCoordinates:
			datum[0] = datum[0] / MaxX
			datum[1] = datum[1] / MaxY
		return DataCoordinates, Classes

	def FindPoles(self,data):
		this = randomelement(data)
		data.remove(this)
		East = farthestfrom(this,data)
		data.remove(East)
		data.append(this)
		West = farthestfrom(East,data)
		data.append(East)
		return East, West
	
	
def main():
	parser = OptionParser()
	parser.add_option("--arff", dest="arff", default=None, metavar="FILE", help="Make arff file to graph.")
	parser.add_option("--n", dest="n", default=4, metavar="N", help="Set n to draw n x n grids.")
	(options, args) = parser.parse_args()
	
	if options.arff == None:
		print "Didn't supply an arff.  *grumble grumble*"
		sys.exit(0)

	arff = Arff(options.arff)
	compassgraph = CompassGraph(arff.data)
	compassgraph.WriteToPNG(options.arff.split('.')[0],int(options.n))

if __name__ == '__main__':
	main()
