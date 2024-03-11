import torch
import math
import torch.nn as nn
import torch.optim as optim
from torchvision import datasets,transforms
from torch.utils.cpp_extension import load
from torch.utils.tensorboard import SummaryWriter
writer = SummaryWriter()

gelu_cpp = load(name="gelu_cpp",sources=["GELU.cpp"])
class GELUF(torch.autograd.Function):
    @staticmethod
    def forward(ctx, input):
        ctx.input=input
        return gelu_cpp.forward(input)
    
    @staticmethod
    def backward(ctx, grad_output):
        input=ctx.input
        return gelu_cpp.backward(grad_output,input)
    
class GELU(nn.Module):
    def forward(self,input):
            return GELUF.apply(input)
    def backward(self,input):
            return GELUF.apply(input)


class LeNet5(nn.Module):
    def __init__(self):
        super(LeNet5,self).__init__()
        self.conv1 = nn.Sequential(nn.Conv2d(1,6,5,1,2),GELU(),nn.MaxPool2d(2,2))
        self.conv2 = nn.Sequential(nn.Conv2d(6,16,5),GELU(),nn.MaxPool2d(2,2))
        self.fc1 = nn.Sequential(nn.Linear(16*5*5,120),GELU())
        self.fc2 = nn.Sequential(nn.Linear(120,84),GELU())
        self.fc3 = nn.Linear(84,10)
    def forward(self,x):
        x = self.conv1(x)
        x = self.conv2(x)
        x = x.view(x.size()[0],-1)
        x = self.fc1(x)
        x = self.fc2(x)
        x = self.fc3(x)
        return x

def train(): 
    model.train()
    global i
    criterion = nn.CrossEntropyLoss()
    for idx, (data, target) in enumerate(train_loader):
        data = data.to(device)
        target = target.to(device)
        optimizer.zero_grad()
        output = model(data)
        loss = criterion(output, target)
        writer.add_scalar("Loss/train", loss, i)
        i = i + 1
        loss.backward()
        optimizer.step()
        if idx % 20 == 0:
            print('Train : Loss is {:.6f}'.format(loss.item()))


def test():
    model.eval()
    correct = 0
    global j
    with torch.no_grad():
        for data, target in test_loader:
            data = data.to(device)
            target = target.to(device)
            output = model(data)
            pred = output.data.max(1, keepdim=True)[1]
            correct += pred.eq(target.data.view_as(pred)).cpu().sum()
            writer.add_scalar("Accuracy/test",100. * correct / len(test_loader.dataset) , j)
            j = j + 1 
        print('\nTest : Accuracy is: {:.2f}%\n'.format(100. * correct / len(test_loader.dataset)))


device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')

train_loader = torch.utils.data.DataLoader(
datasets.MNIST('./MNIST', train=True, download=True, transform=transforms.Compose([transforms.ToTensor(), transforms.Normalize((0.1307,), (0.3081,))])), batch_size=64, shuffle=True)
test_loader = torch.utils.data.DataLoader(datasets.MNIST('./MNIST', train=False, transform=transforms.Compose([transforms.ToTensor(), transforms.Normalize((0.1307,), (0.3081,))])), batch_size=1000, shuffle=True)

model = LeNet5().to(device)
optimizer = torch.optim.Adam(model.parameters(), lr=0.001, betas=(0.9,0.999))
i = 0
j = 0
for epoch in range(10): 
    train()
    test()
