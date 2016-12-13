# k8s-docs

## Build k8s environment on bare metal machine(CentOS).

Follow the instruction in [install k8s on CentOS](http://kubernetes.io/docs/getting-started-guides/centos/centos_manual_config/).

Components on master node: kube-apiserver,kube-scheduler,kube-controller-manager
Components on node: kubelet,kube-proxy

Installation step:

1. Use yum install kubernetes rpm package on master and node.
2. Add hostname and IP mappings in /etc/hosts
3. Config ETCD service on individual machines (etcd provide distributed(raft), consistent key-value store service for shared configuration and service discovery).
4. Update k8s config files: 
master: /etc/kubernetes/config, /etc/kubernetes/apiserver, /etc/kubernetes/controller-manager, /etc/kubernetes/scheduler
node: /etc/kubernetes/config, /etc/kubernetes/kubelet, /etc/kubernetes/proxy
5. Config flanneld on Nodes
6. Start kubernetes service on master and node:
master: kube-apiserver kube-scheduler kube-controller-manager
node: kubelet kube-proxy docker

## Docker: storage issue

```
-g, --graph=""
Path to use as the root of the Docker runtime. Default is /var/lib/docker.
```
This option is different from the storage option for docker-daemon
```
Docker  uses  storage  backends  (known  as "graphdrivers" in the Docker internals) to create writable containers from images.  Many of these backends use operating system level
technologies and can be configured.

Specify options to the storage backend with --storage-opt flags. The only backend that currently takes options is devicemapper. Therefore use these flags with -s=devicemapper.

Specifically for devicemapper, the default is a "loopback" model which requires no pre-configuration, but is extremely inefficient.  Do not use it in production.

To make the best use of Docker with the devicemapper backend, you must have a recent version of LVM.  Use lvm to create a thin pool; for more information see man lvmthin.  Then,
use --storage-opt dm.thinpooldev to tell the Docker engine to use that pool for allocating images and container snapshots.

```

## ETCD and Flannel

### ETCD
https://github.com/coreos/etcd
Using [Raft](https://raft.github.io/), a consensus algorithm.
[How to build etcd clustering](https://github.com/coreos/etcd/blob/master/Documentation/op-guide/clustering.md)

### Flannel
[How to setup k8s networking with flannel](http://severalnines.com/blog/installing-kubernetes-cluster-minions-centos7-manage-pods-services)
Flanneld create its networking interface using config file in etcd, then use command line option to connect with docker networking.
```
# show the detail of connection between docker and flanneld
sudo systemctl show docker
```
in file "/usr/lib/systemd/system/flanneld.service"
create the "DOCKER_NETWORK_OPTIONS" and dependences for docker

in the file /usr/lib/systemd/system/docker.service.d/flannel.conf
setup option file /run/flannel/docker, in which "--bip" option is used to setup connection between docker and flannel.
