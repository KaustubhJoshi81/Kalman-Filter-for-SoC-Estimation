# Kalman-Filter-for-SoC-Estimation
As a part of acedemic curriculum, our project group is working on Active Battery Management System. Our goal with this project is to come up with our own circuit instead of using Monolithic ICs. The system is divided into three parts: SoC estimation, Cell-Balancing and Battery pack Protection. I am working on SoC estimation. 
I have designed a PCB using eagle, which measures the cell-voltage and cell-current and also designed analog accmulator which acts as a coulomb counter. In the future, I want to integrate the analog coulomb counter int the SoC estimation algorithm.
Currently, I am working on the SoC estimation algorithm. The algortihm uses Resistive cell model and Extended Kalman Filter to linearlize the OCV-SoC curve.  


