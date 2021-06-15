# Get the base Ubuntu image from Docker Hub
FROM ubuntu:20.04
LABEL maintainer="Mykhailo_Lohvynenko@epam.com"

# Configure the geographic area
ENV TZ=Europe/Kiev
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

# Update apps on the base image
RUN apt-get -y update
RUN apt-get install -y sudo

# Install the GNU compiler collection
RUN apt-get install -y build-essential

# Install cmake
RUN apt-get install -y cmake

# Install GNU debbuger
RUN apt-get install -y gdb

# Install git
RUN apt-get -y install git

# Install nano
RUN apt-get -y install nano

# create a user in sudo group 
ENV user=student
RUN useradd -m ${user}
RUN usermod -aG sudo ${user}

# change password
RUN echo "${user}:${user}" | chpasswd

# change user
USER $user
WORKDIR /home/$user

CMD [ "bash" ]