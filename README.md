# SamuStroop
[Samu](http://arxiv.org/abs/1511.02889) (Hanshon) experiencing with the Stroop effect
This is an example of the manuscript entitled "Samu in his prenatal development".

This project uses the same COP-based Q-learning engine as Samu ([Nahshon](https://github.com/nbatfai/nahshon)) 
to predict the next sentences of a conversation. 

After the basic work on the joining 
of Conway's Game of Life and Samu's COP engine is [done](https://github.com/nbatfai/SamuLife), 
I had started to work on creating a similar but much simpler example 
in which Samu must learn the frames of the [moving picture](https://github.com/nbatfai/SamuMovie).

The experiments started in this project are based on an even simpler model in which Samu must learn stills.

## Usage

```
git clone https://github.com/nbatfai/SamuStroop.git
cd SamuStroop/
~/Qt/5.5/gcc_64/bin/qmake SamuLife.pro
make
./SamuStroop
```
[https://youtu.be/VujHHeYuzIk](https://youtu.be/VujHHeYuzIk)

![samustroop](https://cloud.githubusercontent.com/assets/3148120/12371932/893eca66-bc45-11e5-9b29-aa19884a551c.png)