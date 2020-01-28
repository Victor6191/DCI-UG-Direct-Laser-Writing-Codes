% code used in Implementation and assessment of a low-cost 3D
%laser platform controlled by open software for
%printing polymeric micro-structures; Camarena-Chávez et al. JMM(IOP)
%any use should be reference as: Camarena-Chávez, V. A., Castro-Beltrán, R., 
% Medina-Cázares, O. M., Álvarez-Martínez, J. U., Ramos-Ortiz, G., & Gutierrez-
%Juarez, G. (2020). Implementation and assessment of a low-cost 
%3D laser platform controlled by open software for printing 
%polymeric micro-structures. Journal of Micromechanics and Microengineering.
clear
close all
clc
tic;
set(0, 'DefaultAxesFontName', 'Times New Roman')
set(0, 'DefaultAxesFontSize', 11)
set(0, 'defaultuicontrolunits', 'normalized');


NA=.25;
n=1.0;
n2=1.59;
lambda=532e-9;
alpha=asin(NA/n);
k=2*pi*n/lambda;
din=150*1e-6;


L_focal=1.0*1e-6+8*1e-6;
Nx=450;
Ny=450;
Nz=450;
x2=linspace(-L_focal, L_focal, Nx);
y2=linspace(-L_focal,L_focal,Ny);
[X2,Y2]=meshgrid(x2,y2);
Z2=112*1e-6;

% '1': x-lineal, '2':y-lineal, '3':circular izq
% '4': circular der, '5': eliptica, '6': radial, '7': azimutal
polar = 1;
polarSTR=num2str(polar);

Ex2=0; 
Ey2=0;
Ez2=0;
N_theta=50;
N_phi=50;
N_theta2=50;
delta_theta=alpha/N_theta;
delta_phi=2*pi/N_phi;
delta_theta2=2*pi/N_theta2;


for theta=eps:delta_theta:alpha
    for phi=eps:delta_phi:2*pi
          
            theta2=asin(n*sin(theta)/n2);
            a=cos(theta)*(cos(phi))^2+ (sin(phi))^2;
            b=cos(theta)*cos(phi)*sin(phi)-(cos(phi)*sin(phi));
            c=sin(theta)*cos(phi);
            d=cos(theta)*(sin(phi))^2 + (cos(phi))^2;
            e=sin(theta)*sin(phi);
            ff=cos(theta);
            tp = (2*sin(theta2)*cos(theta))/(sin(theta+theta2)*cos(theta-theta2));
            ts = (2*sin(theta2)*cos(theta))/sin(theta+theta2);
            g=tp*(cos(theta)*cos(theta2)+sin(theta)*sin(theta2));
            h=tp*(cos(theta2)*sin(theta)-cos(theta)*sin(theta2));
            FI  = -din*(n*cos(theta)-n2*cos(theta2));
            V2 = [g 0 -h;0 ts 0;b 0 h];
            V1=[a b c;b d e;-c -e ff];
            V=[((g*a)+(h*c)) ((g*b)+(h*e)) ((g*c)+(-h*ff));ts*b ts*d ts*e;((h*a)+(g*-c)) ((h*b)+(g*-e)) ((h*c)+(g*ff))];
            %V = V2*V1;
            px=[1,0,1/sqrt(2), 1i/sqrt(2), 2/sqrt(5),cos(phi),sin(phi)];
            py=[0,1,1i/sqrt(2),1/sqrt(2),1i/sqrt(5),sin(phi),cos(phi)];
            pz=0;
            P=[px(1,polar);py(1,polar);pz];
            PP=V*P;
            A=1;
            Ex2=Ex2+1i*sin(theta)*sqrt(cos(theta)).*PP(1,1).*exp(1i*k*(n2*Z2.*cos(theta2)+((n*sin(theta)).*(X2.*cos(phi)+Y2.*sin(phi)))+FI))*delta_theta*delta_phi;
            Ey2=Ey2+1i*sin(theta)*sqrt(cos(theta)).*PP(2,1).*exp(1i*k*(n2*Z2.*cos(theta2)+((n*sin(theta)).*(X2.*cos(phi)+Y2.*sin(phi)))+FI))*delta_theta*delta_phi;
            Ez2=Ez2+1i*sin(theta)*sqrt(cos(theta)).*PP(3,1).*exp(1i*k*(n2*Z2.*cos(theta2)+((n*sin(theta)).*(X2.*cos(phi)+Y2.*sin(phi)))+FI))*delta_theta*delta_phi;
    end
end
Ex2=-(1/lambda).*Ex2;
Ey2=-(1/lambda).*Ey2;
Ez2=-(1/lambda).*Ez2;
Ix2=conj(Ex2).*(Ex2);
Iy2=conj(Ey2).*(Ey2);
Iz2=conj(Ez2).*(Ez2);
I1=Ix2+Iy2+Iz2;
save('Iz2_0.25.txt', 'Iz2', '-ascii','-double', '-tabs')

figure (1)
hFig=figure(1);
set(gcf,'PaperPositionMode','auto')
set(hFig,'Position',[290 290 400 400])
p=axes;
set(p,'Position',[0.1 0.15 0.8 0.8]) 
pcolor(X2,Y2,I1);
c = colorbar;
c.Label.String = 'I (W)';
shading interp
title('      NA =0.25,z=15 um')
set(gca,'Xtick',[-L_focal 0 L_focal])
set(gca,'Ytick',[-L_focal 0 L_focal])
set(gca,'Fontsize',14)
xlabel('m','Fontsize',14)
ylabel('m','Fontsize',14)
axis equal
axis tight
hold off
colormap hot;

dataname=['polar=',polarSTR];
saveas(hFig,['spot','.png']);

toc
load chirp