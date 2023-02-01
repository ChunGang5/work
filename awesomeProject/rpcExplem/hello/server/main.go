package main

import (
	"awesomeProject/rpcExplem/hello/hello"
	"github.com/golang/protobuf/proto"
	"github.com/golang/protobuf/protoc-gen-go/descriptor"
	"github.com/golang/protobuf/protoc-gen-go/generator"
	"io/ioutil"
	"os"
)

// ###################简单的RPC

//type HelloService struct {
//}

//func (p *HelloService) Hello(request string, reply *string) error {
//	fmt.Println(request)
//	*reply = "hello: " + request
//	return nil
//}
//
//func (p *HelloService) Add(request int, reply *int) error {
//	*reply = request + 5
//	return nil
//}
//
//func main() {
//	//RegisterHelloService(new(HelloService))
//	rpc.RegisterName("HelloService", new(HelloService))
//	listener, err := net.Listen("tcp", ":1234")
//	if err != nil {
//		log.Fatal("ListenTcp error:", err)
//	}
//
//	fmt.Println("server start")
//
//	//for {
//	//	conn, err := listener.Accept()
//	//	if err != nil {
//	//		log.Fatal("Accept error:", err)
//	//	}
//	//	// 协程
//	//	go rpc.ServeCodec(jsonrpc.NewServerCodec(conn))
//	//}
//	for {
//		conn, err := listener.Accept()
//		if err != nil {
//			log.Fatal("Accept error:", err)
//		}
//		rpc.ServeConn(conn)
//	}
//
//
//}

type HelloServer struct {
}

func (p *HelloServer) Hello(request *hello.String, reply *hello.String) error {
	reply.Value = "hello: " + request.GetValue()
	return nil
}

type netrpcPlugin struct{ *generator.Generator }

func (p *netrpcPlugin) Name() string                { return "netrpc" }
func (p *netrpcPlugin) Init(g *generator.Generator) { p.Generator = g }

func (p *netrpcPlugin) GenerateImports(file *generator.FileDescriptor) {
	if len(file.Service) > 0 {
		p.genImportCode(file)
	}
}

func (p *netrpcPlugin) Generate(file *generator.FileDescriptor) {
	for _, svc := range file.Service {
		p.genServiceCode(svc)
	}
}

func (p *netrpcPlugin) genImportCode(file *generator.FileDescriptor) {
	p.P("// TODO: import code")
}

func (p *netrpcPlugin) genServiceCode(svc *descriptor.ServiceDescriptorProto) {
	p.P("//TODO: service code, name =" + svc.GetName())
}

func init() {
	generator.RegisterPlugin(new(netrpcPlugin))
}

func main() {
	g := generator.New()

	data, err := ioutil.ReadAll(os.Stdin)
	if err != nil {
		g.Error(err, "reading input")
	}

	if err := proto.Unmarshal(data, g.Request); err != nil {
		g.Error(err, "parsing input proto")
	}

	if len(g.Request.FileToGenerate) == 0 {
		g.Fail("no files to generate")
	}

	g.CommandLineParameters(g.Request.GetParameter())

	// Create a wrapped version of the Descriptors and EnumDescriptors that
	// point to the file that defines them.
	g.WrapTypes()

	g.SetPackageNames()
	g.BuildTypeNameMap()

	g.GenerateAllFiles()

	// Send back the results.
	data, err = proto.Marshal(g.Response)
	if err != nil {
		g.Error(err, "failed to marshal output proto")
	}
	_, err = os.Stdout.Write(data)
	if err != nil {
		g.Error(err, "failed to write output proto")
	}
}
