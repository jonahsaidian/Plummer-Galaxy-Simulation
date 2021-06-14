%x = xearth;
% file input:
% fid = fopen('./demo_x.txt', 'rt');
% x = textscan(fid, '%f\n');
% fclose(fid);
% x = cell2mat(x);

file_out = './plummer.gif';

figure(1);
for j = 1:size(xf,1)
   % y = yearth;
   % for i=1:n
   %     xtemp=[];
   %     ytemp=[];
   %     xtemp=x(1:i);
   %     ytemp=y(1:i);
   % end
   n=1000;
   % for i=1:n
    scatter3(xf(j,:),yf(j,:),zf(j,:),3);
    %plot(xf(:,i),yf(:,i));
   % end
    xlabel('x (Kpc)');
    ylabel('y (Kpc)');
    title('plummer 1000 points');
    axis([-4e0 4e0 -4e0 4e0]);
    hold on
    drawnow;

    % figure number
    frame = getframe(1);

    im = frame2im(frame);

    % pixel intensity (uint8), colormap
    [imind, cm] = rgb2ind(im, 256);

    if j == 1;
        % image data (uint8), colormap, format
        imwrite(imind, cm, file_out, 'gif', 'Loopcount', inf); % # number repeats
    else
        imwrite(imind, cm, file_out, 'gif', 'WriteMode', 'append');
    end
    %# word argument 'DelayTime' can be used to set the time between frames in seconds (0.5 s default)
    hold off
end