class People: 
	def __init__(self, name, age):
		self.name = name
		self.age = age

	def sayHi(self):
		print(f"{self.name} говорит привет")

	def sayAge(self):
		print(f"{self.name, self.age}")


class Denis(People):
		def __init__(self, name, age, group):
			super().__init__(name,age)
			self.group = group
				
		def sayGroup(self):
			print(f"{self.name} учится в группе {self.group}")


denis = Denis('Denis', 18, 'ИП-391к')

denis.sayHi()
denis.sayAge()
denis.sayGroup()