use winit::{
    event::{Event, WindowEvent},
    event_loop::{ControlFlow, EventLoop},
    window::WindowBuilder,
}
use wgpu::util::DeviceExt;

async fn run(){
    let event_loop = EventLoop::new();
    let window = WindowBuilder::new().with_title("Text Editor").build(&event_loop).unwrap();
    let instance = wgpu::Instance::default();
    let surface = unsafe{instance.create_surface(&window)}.unwrap();
    let adapter = instance.request_adapter(&wgpu::RequestAdapterOptions{
        power_preference:wgpu::PowerPreference::HighPerformance,
        compatible_surface:Some(&surface),
        ..Default::default()
    }).await.unwrap();
    let (device,queue)=adapter.request_device(&wgpu::DeviceDescriptor{
        features:wgpu::Features::empty(),
        limits:wgpu::Limits::default(),
        label:None,
    },None,).await.unwrap();
}

fn main() {
    println!("Hello, world!");
}
