class TextInterface:
    def __init__(self):
        print("Welcome to Currency Converter!")
        self.qFlag = False       # Quit flag
        self.fc = 'USD'          # foreign currency selected
        self.to = 'RMB'          # convert to?
        self.amt = 0             # amount to be converted

    def getInfo(self):
        self.qFlag = self.getQFlag()
        if self.qFlag:
            self.close()
        else:
            self.fc = self.getFC()
            self.to = self.getTo()
            self.amt = self.getAmount()
        return self.qFlag,self.fc,self.to,self.amt

    def getQFlag(self):
        ans = raw_input("Want to quit? (y/n) ")
        if ans[0] in 'yY':
            return True
        else:
            return False

    def getFC(self):
        return raw_input("Choose among {USD,Euro,Yen,Pound}: ")
    
    def getTo(self):
        ans = raw_input("Convert to RMB? (y/n) ")
        if ans[0] in 'yY':
            return 'RMB'
        else:
            return self.fc
        
    def getAmount(self):
        if self.to == 'RMB':
            return input("How much " + self.fc + "? ")
        else:
            return input("How much RMB? ") 
    
    def showInfo(self,r):
        if self.to == 'RMB':
            print "%.2f %s ==> %.2f RMB" % (self.amt,self.fc,r)
        else:
            print "%.2f RMB ==> %.2f %s" % (self.amt,r,self.fc)
        
    def close(self):
        print("Goodbye!")
