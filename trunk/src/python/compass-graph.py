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

	def __init__(self, InputData,Parameters):
		self.data = InputData
		(self.West, self.East) = self.FindPoles(InputData)
		(self.DataCoordinates, self.Classes) = self.ComputeCoordinates(Parameters)
		if Parameters.Magnetic is True:
			EastSide = 0
			WestSide = 0
			# check to see if more points are at the other pole.  If so, we switch the poles.  Might be a better way to do this.  Will think about it.
			for datum in self.DataCoordinates :
				if datum[0] >= 0.5:
					EastSide = EastSide + 1
				else:
					WestSide = WestSide + 1
			if (EastSide > WestSide):
				print("switching poles")
				tmp = self.East
				self.East = self.West
				self.West = tmp
				(self.DataCoordinates, self.Classes) = self.ComputeCoordinates(Parameters)
				
	def WriteToPNG(self,filename,Parameters):
		self.DataCoordinates = self.DataCoordinates.transpose()
		fig = plt.figure()
		ax1 = fig.add_axes([0.1,0.1,0.85,0.85])
		ticks = []
		for i in range(Parameters.n):
			ticks.append( ( float(i)+1.0 )* (1.0/float(Parameters.n) ) )
		#ax1.set_xticks(ticks)
		#ax1.set_yticks(ticks)
		plt.title(filename)
		plt.xlabel("x")
		plt.ylabel("y")
		for ax in fig.axes:
			ax.grid(True)

		if isinstance(self.Classes[0][0],str):
			for i in range(len(self.DataCoordinates[0])):
				if self.Classes[i][0].upper() == "TRUE":
					ax1.plot(self.DataCoordinates[0][i],self.DataCoordinates[1][i],"bo",markersize=3)
				else:
					ax1.plot(self.DataCoordinates[0][i],self.DataCoordinates[1][i],"ro",markersize=3)
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
			
#		if Parameters.Normalize == True:
#			ax1.set_xbound(0,1)
#			ax1.set_ybound(0,1)

		plt.show()

				

	def ComputeCoordinates(self,Parameters):
		d = distance(self.East,self.West)
		MaxX = 0
		MaxY = 0
		DataCoordinates = None
		if Parameters.NoPlotPole is True:
			self.data.remove(self.East)
			self.data.remove(self.West)
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
			if Parameters.Normalize is True:
				datum[0] = datum[0] / MaxX
				datum[1] = datum[1] / MaxY
			if Parameters.logX is True:
				datum[0] = math.log(datum[0]+0.0001)
			if Parameters.logY is True:
				datum[1] = math.log(datum[1]+0.0001)
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

class CompassGraphParameters:
	n = 4
	logX = False
	logY = False
	Magnetic = False
	Normalize = False
	inputPolePlot = False
	
	def __init__(self, inputN, inputlogX, inputlogY, inputMagnetic,inputNormalize,inputPolePlot):
		self.n = int(inputN)
		self.logX = inputlogX
		self.logY = inputlogY
		self.Magnetic = inputMagnetic
		self.Normalize = inputNormalize
		self.NoPlotPole = inputPolePlot
	
	
def main():
	ErrorState = "n"
	parser = OptionParser()
	parser.add_option("--arff", dest="arff", default=None, metavar="FILE", help="Make arff file to graph.")
	parser.add_option("--n", dest="n", default=4, metavar="N", help="Set n to draw n x n grids.")
	parser.add_option("--logX", dest="logX", default=False, metavar="NONE", action="store_true", help="Apply a log to X axis values")
	parser.add_option("--logY", dest="logY",default=False, metavar="NONE", action="store_true", help="Apply a log to Y axis values")
	parser.add_option("--magnetic", dest="magnetic", default=False, metavar="NONE", action="store_true", help="Force the West pole to be more densely populated. Useful for --logX and --logY")
	parser.add_option("--nonormalize",dest="normalize",default=True, metavar="NONE", action="store_false", help="Prevents normalization of data between 0 and 1.")
	parser.add_option("--noplotpole",dest="noplotpole",default=False,metavar="NONE",action="store_true", help="Remove the poles from the dataset when plotting.")
	(options, args) = parser.parse_args()
	
	if options.arff == None:
		print "Didn't supply an arff.  *grumble grumble*"
		ErrorState = "y"
	
	if ErrorState == "y":
		print "Missing critical arguments.  Aborting."
		sys.exit(-1)
			
	arff = Arff(options.arff)

	# Created a data structure CompassGraphParameters we can use to easily carry parameters between functions.  Better ideas are welcome.
	# Might be better to overload the constructor to accept a sequence.
	# Also, I'm not a fan of how many arguments this constructor is getting.  Must be a better way.
	parameters = CompassGraphParameters(options.n,options.logX, options.logY, options.magnetic, options.normalize, options.noplotpole)

	compassgraph = CompassGraph(arff.data,parameters)
	compassgraph.WriteToPNG(options.arff.split('.')[0],parameters)

if __name__ == '__main__':
	main()
