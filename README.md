当一个系统中的配置文件发生改变的时候，我们需要重新启动该服务，才能使得新的配置文件生效，spring cloud config可以实现微服务中的所有系统的配置文件的统一管理，而且还可以实现当配置文件发生变化的时候，系统会自动更新获取新的配置。在spring cloud config 组件中，分两个角色，一是config server，二是config client。


1.搭建git仓库, https://github.com/JasonSparrow/config.git
2.创建config-client-dev.properties文件, config-client-dev这个文件名称格式是固定的, 后面你可以自己修改时dev, 或者是test, 客户端会根据这个字段来区分读取哪个配置文件.
3.在config-client-dev.properties文件设置值userName=Jason
4.上传config-client-dev.properties到仓库

![分布式配置中心流程图](https://upload-images.jianshu.io/upload_images/1599230-0ca2bab9f3440c33.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

###config-server项目搭建
pom文件依赖
```
<parent>
		<groupId>org.springframework.boot</groupId>
		<artifactId>spring-boot-starter-parent</artifactId>
		<version>1.5.2.RELEASE</version>
		<relativePath /> <!-- lookup parent from repository -->
	</parent>

	<properties>
		<project.build.sourceEncoding>UTF-8</project.build.sourceEncoding>
		<project.reporting.outputEncoding>UTF-8</project.reporting.outputEncoding>
		<java.version>1.8</java.version>
	</properties>

	<dependencies>
		<dependency>
			<groupId>org.springframework.cloud</groupId>
			<artifactId>spring-cloud-config-server</artifactId>
		</dependency>

		<dependency>
			<groupId>org.springframework.boot</groupId>
			<artifactId>spring-boot-starter-test</artifactId>
			<scope>test</scope>
		</dependency>

		<dependency>
			<groupId>org.springframework.cloud</groupId>
			<artifactId>spring-cloud-starter-eureka</artifactId>
		</dependency>
	</dependencies>

	<dependencyManagement>
		<dependencies>
			<dependency>
				<groupId>org.springframework.cloud</groupId>
				<artifactId>spring-cloud-dependencies</artifactId>
				<version>Camden.SR6</version>
				<type>pom</type>
				<scope>import</scope>
			</dependency>
		</dependencies>
	</dependencyManagement>


	<build>
		<plugins>
			<plugin>
				<groupId>org.springframework.boot</groupId>
				<artifactId>spring-boot-maven-plugin</artifactId>
			</plugin>
		</plugins>
	</build>

	<repositories>
		<repository>
			<id>spring-milestones</id>
			<name>Spring Milestones</name>
			<url>https://repo.spring.io/milestone</url>
			<snapshots>
				<enabled>false</enabled>
			</snapshots>
		</repository>
	</repositories>
```

application.properties 配置文件, 或者application.yml
```
spring.application.name=config-server
server.port=8889
spring.cloud.config.server.git.uri=https://github.com/JasonSparrow/config.git
spring.cloud.config.server.git.searchPaths=respo
spring.cloud.config.label=master
spring.cloud.config.server.git.username=
spring.cloud.config.server.git.password=
```
spring.cloud.config.server.git.uri：配置git仓库地址
spring.cloud.config.server.git.searchPaths：配置仓库路径
spring.cloud.config.label：配置仓库的分支
spring.cloud.config.server.git.username：访问git仓库的用户名
spring.cloud.config.server.git.password：访问git仓库的用户密码

启动config-server项目
```
@SpringBootApplication
@EnableConfigServer
public class ConfigServerApp {
	public static void main(String[] args) {
		SpringApplication.run(ConfigServerApp, args);
	}
}
```

@EnableConfigServer 开启SpringCloudConfig服务端

###config-client项目搭建

pom依赖
```
<parent>
		<groupId>org.springframework.boot</groupId>
		<artifactId>spring-boot-starter-parent</artifactId>
		<version>1.5.2.RELEASE</version>
		<relativePath /> <!-- lookup parent from repository -->
	</parent>

	<properties>
		<project.build.sourceEncoding>UTF-8</project.build.sourceEncoding>
		<project.reporting.outputEncoding>UTF-8</project.reporting.outputEncoding>
		<java.version>1.8</java.version>
	</properties>

	<dependencies>
		<dependency>
			<groupId>org.springframework.cloud</groupId>
			<artifactId>spring-cloud-starter-config</artifactId>
		</dependency>

		<dependency>
			<groupId>org.springframework.boot</groupId>
			<artifactId>spring-boot-starter-web</artifactId>
		</dependency>

		<dependency>
			<groupId>org.springframework.boot</groupId>
			<artifactId>spring-boot-starter-test</artifactId>
			<scope>test</scope>
		</dependency>
	</dependencies>

	<dependencyManagement>
		<dependencies>
			<dependency>
				<groupId>org.springframework.cloud</groupId>
				<artifactId>spring-cloud-dependencies</artifactId>
				<version>Dalston.RC1</version>
				<type>pom</type>
				<scope>import</scope>
			</dependency>
		</dependencies>
	</dependencyManagement>

	<build>
		<plugins>
			<plugin>
				<groupId>org.springframework.boot</groupId>
				<artifactId>spring-boot-maven-plugin</artifactId>
			</plugin>
		</plugins>
	</build>

	<repositories>
		<repository>
			<id>spring-milestones</id>
			<name>Spring Milestones</name>
			<url>https://repo.spring.io/milestone</url>
			<snapshots>
				<enabled>false</enabled>
			</snapshots>
		</repository>
	</repositories>
```

bootstrap.properties配置文件
```
#上传到git的文件名config-client-dev.properties
#config-client 名称要一样
spring.application.name=config-client
#分支
spring.cloud.config.label=master
#文件名
spring.cloud.config.profile=dev
#要读取的服务器的地址
spring.cloud.config.uri= http://localhost:8889/
server.port=8881
```
获取配置中的值
```
@RestController
public class TestController {

	@Value("${userName}")
	private String userName;

	@RequestMapping("/getUserName")
	public String getUserName() {
		return userName;
	}
}
```
```@Value("${userName}")```将会去读取配置中心config-client-dev.properties文件中userName的值

启动config-client
```
@SpringBootApplication
public class ConfigClientApp {

	public static void main(String[] args) {
		SpringApplication.run(ConfigClientApp.class, args);
	}

}
```

以上config-server和config-client都是在本地启动的, 同样, 也可以把他们都注册到eureka上, 只需要在配置文件中添加如下配置即可.
```
###服务注册到eureka地址
eureka:
  client:
    service-url:
           defaultZone: http://localhost:8100/eureka
```
