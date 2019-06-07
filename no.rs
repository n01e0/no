use std::env;

fn main(){
    let expletive = 
        env::args().nth(1).unwrap_or("n".into());
    loop{
        println!("{}",expletive);
    }
}
