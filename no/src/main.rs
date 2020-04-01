#[macro_use]
extern crate clap;

fn main() {
    let matches = clap_app!(myapp =>
                    (version:   crate_version!())
                    (author:    crate_authors!())
                    (about:     crate_description!())
                    (@arg word: "word replacing no"))
                    .get_matches();

    if let Some(word) = matches.value_of("word") {
        loop {
            println!("{}", word);
        }
    } else {
        loop {
            println!("n");
        }
    }
}
