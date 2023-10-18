package dbp7.controller;

import dbp7.entity.Club;    //Club.java 경로
import dbp7.repository.ClubRepository;  //ClubRepository.java 경로
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.util.List;
import java.util.Optional;

@RestController
@RequestMapping("/")
public class ClubController {
    @Autowired
    ClubRepository clubRepository;

    @GetMapping("/all")     //club 테이블 전체 검색
    public List<Club> getAllClubs(){
        return clubRepository.getAllClubs();
    }

    @GetMapping("/id/{id}")     //id로 검색
    public Optional<Club> getClub(@PathVariable int id){
        return clubRepository.getClub(id);
    }

    @GetMapping("/addClub")     //데이터 삽입
    public String addClub(@RequestParam("id") int id,@RequestParam("name") String name,
                          @RequestParam("category") String category){
        if(clubRepository.addClub(id,name,category) >= 1){
            return "Club Added";
        }else{
            return "Not Added";
        }
    }

    @DeleteMapping("/delete/{id}")     //데이터 삭제
    public String deleteClub(@PathVariable int id) {
        if(clubRepository.deleteClub(id) >= 1){
            return "Club Deleted";
        }else{
            return "Not Deleted";
        }
    }
}


